#pragma once
#include "Ping/Types.h"
#include "VulkanCommon.h"
#include <optional>
#include <stdexcept>

/**
 * @file
 * `Backend::ToVulkan` overloads bridging each `Ping` enum to its Vulkan equivalent, plus the few
 * `Backend::ToPing` overloads needed where a value originates in Vulkan (a driver-reported surface
 * format, for instance) and has to be handed back out through the `Ping` API. This is the one place
 * that translation happens; a new `Ping` enum value needs a corresponding case/flag check added to
 * its overload here (see CLAUDE.md's "Architecture" section).
 */

namespace Backend
{
/** @throws std::runtime_error if `layout` has no known `vk::ImageLayout` mapping. */
vk::ImageLayout ToVulkan(Ping::ImageLayout layout);

vk::ImageAspectFlags ToVulkan(Ping::ImageAspect aspect);

/** Bitwise-ORs together the `vk::AccessFlagBits2` for every flag set in `mask`. */
vk::AccessFlags2 ToVulkan(Ping::AccessMask mask);

/** Bitwise-ORs together the `vk::PipelineStageFlagBits2` for every flag set in `stage`. */
vk::PipelineStageFlags2 ToVulkan(Ping::PipelineStage stage);

/** Bitwise-ORs together the `vk::BufferUsageFlagBits` for every flag set in `usage`. */
vk::BufferUsageFlags ToVulkan(Ping::BufferUsage usage);

/** Bitwise-ORs together the `vk::CommandBufferUsageFlags` for every flag set in `usage`. */
vk::CommandBufferUsageFlags ToVulkan(Ping::CommandBufferUsage usage);

/** Bitwise-ORs together the `vk::MemoryPropertyFlagBits` for every flag set in `property`. */
vk::MemoryPropertyFlags ToVulkan(Ping::MemoryProperty property);

/** @note Aborts via `assert` if `format` has no known `vk::Format` mapping. */
vk::Format ToVulkan(Ping::VertexFormat format);

/** @throws std::runtime_error if `format` has no known `vk::Format` mapping. */
vk::Format ToVulkan(Ping::Format format);

/**
 * Maps a driver-reported `vk::Format` back to its `Ping::Format` equivalent, or `std::nullopt` if
 * `format` is outside the subset `Ping::Format` mirrors.
 *
 * Use this over `ToPing` when picking a format out of a driver-reported list (surface formats, for
 * instance), where an unmappable entry is a candidate to skip rather than an error.
 */
std::optional<Ping::Format> TryToPing(vk::Format format);

/**
 * Maps a driver-reported `vk::Format` back to its `Ping::Format` equivalent.
 *
 * @warning Throws rather than falling back to `Ping::Format::Undefined`. `Ping::Format` mirrors only
 * a subset of `vk::Format`, and a silent `Undefined` would travel all the way to a pipeline's colour
 * attachment format, where it can never match the images that pipeline renders into — a loud failure
 * at selection time is far cheaper to diagnose than a mismatch at draw time.
 * @throws std::runtime_error if `format` is outside the subset `Ping::Format` mirrors. Prefer
 * `TryToPing` where the caller can pick a different format instead.
 */
Ping::Format ToPing(vk::Format format);

/** Bitwise-ORs together the `vk::ShaderStageFlagBits` for every flag set in `stage`. */
vk::ShaderStageFlags ToVulkan(Ping::ShaderStage stage);

/** @throws std::runtime_error if `type` has no known `vk::DescriptorType` mapping. */
vk::DescriptorType ToVulkan(Ping::DescriptorType type);

/** Bitwise-ORs together the `vk::ImageUsageFlagBits` for every flag set in `usage`. */
vk::ImageUsageFlags ToVulkan(Ping::ImageUsage usage);

vk::Filter ToVulkan(Ping::SamplerFilterMode filter);

vk::SamplerMipmapMode ToVulkan(Ping::SamplerMipMapMode mipmap_mode);

vk::SamplerAddressMode ToVulkan(Ping::SamplerAddressMode address_mode);

vk::CullModeFlags ToVulkan(Ping::CullMode cull_mode);

vk::BlendFactor ToVulkan(Ping::BlendFactor blend_factor);
} // namespace Backend